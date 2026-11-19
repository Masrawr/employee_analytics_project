"""Read xctrace XML tables, resolving its per-file ID references."""
import xml.etree.ElementTree as ET
import gzip
from pathlib import Path


def rows(path):
    ids = {}
    columns = []
    path = Path(path)
    source = path if path.exists() else gzip.open(str(path)+'.gz', 'rb')
    for event, element in ET.iterparse(source, events=('end',)):
        if element.tag == 'schema':
            columns = [col.findtext('mnemonic') for col in element.findall('col')]
        elif element.tag == 'row':
            for child in element.iter():
                if 'id' in child.attrib:
                    ids[child.attrib['id']] = (child.text or child.get('fmt', ''), child.get('fmt', ''))
            values = []
            for child in element:
                if child.get('ref'):
                    value, formatted = ids[child.get('ref')]
                else:
                    value, formatted = child.text or child.get('fmt', ''), child.get('fmt', '')
                values.append((value, formatted))
            yield dict(zip(columns, values))
            element.clear()
